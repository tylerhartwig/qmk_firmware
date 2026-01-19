import ezdxf
import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import splprep, splev
import math

# --- CONFIGURATION ---
FILENAME = 'Shell V3 - Sketch 11.dxf'
NUM_LEDS = 65
VISUALIZE = True

# --- REVERSE DIRECTION ---
# Set to True to make the rainbow flow the opposite way
REVERSE_DIRECTION = True

# --- COORDINATE SPACE ---
# Fits the design into this box (Safe Zone)
QMK_MIN_X = 160
QMK_MAX_X = 224
QMK_MIN_Y = 0
QMK_MAX_Y = 64

# True = Keep circles circular. False = Stretch to fill box.
PRESERVE_ASPECT_RATIO = True

# --- PATH TUNING ---
JOIN_TOLERANCE = 1.0
TARGET_PATH_INDEX = 0

# --- ORIENTATION ---
FLIP_X_AXIS = False
FLIP_Y_AXIS = True
MANUAL_ROTATION = 3
AUTO_FIND_NOTCH = True


# ------------------------------------------------------------------

def dist(p1, p2):
    return math.hypot(p1[0] - p2[0], p1[1] - p2[1])


def get_2d_point(point_3d):
    return (point_3d[0], point_3d[1])


def get_points_from_entity(entity):
    points = []
    try:
        if entity.dxftype() == 'SPLINE':
            raw_pts = entity.construction_tool().flattening(distance=0.5)
            points = [get_2d_point(p) for p in raw_pts]
        elif entity.dxftype() == 'LWPOLYLINE':
            points = [get_2d_point(p) for p in entity.get_points()]
        elif entity.dxftype() == 'LINE':
            points = [get_2d_point(entity.dxf.start), get_2d_point(entity.dxf.end)]
        elif entity.dxftype() == 'ARC' or entity.dxftype() == 'CIRCLE':
            is_circle = (entity.dxftype() == 'CIRCLE')
            start_angle = 0 if is_circle else math.radians(entity.dxf.start_angle)
            end_angle = 2 * math.pi if is_circle else math.radians(entity.dxf.end_angle)
            if not is_circle and end_angle <= start_angle: end_angle += 2 * math.pi
            radius = entity.dxf.radius
            center = get_2d_point(entity.dxf.center)
            res = 40 if is_circle else 20
            angles = np.linspace(start_angle, end_angle, res)
            points = [(center[0] + radius * math.cos(a), center[1] + radius * math.sin(a)) for a in angles]
            if is_circle: points.append(points[0])
    except:
        return []
    return points


def join_segments(segments, tolerance=0.1):
    if not segments: return []
    merged_paths = [segments.pop(0)]
    while segments:
        changed = False
        for i, path in enumerate(merged_paths):
            path_start, path_end = path[0], path[-1]
            for j, seg in enumerate(segments):
                seg_start, seg_end = seg[0], seg[-1]
                if dist(path_end, seg_start) < tolerance:
                    path.extend(seg[1:])
                    segments.pop(j);
                    changed = True;
                    break
                elif dist(path_end, seg_end) < tolerance:
                    path.extend(seg[::-1][1:])
                    segments.pop(j);
                    changed = True;
                    break
                elif dist(seg_end, path_start) < tolerance:
                    merged_paths[i] = seg[:-1] + path
                    segments.pop(j);
                    changed = True;
                    break
                elif dist(seg_start, path_start) < tolerance:
                    merged_paths[i] = seg[:-1][:-1] + path
                    segments.pop(j);
                    changed = True;
                    break
            if changed: break
        if not changed and segments:
            merged_paths.append(segments.pop(0))
    return merged_paths


def sort_nearest_neighbor(points):
    if not points: return []
    sorted_pts = [points.pop(0)]
    while points:
        last = sorted_pts[-1]
        nearest_idx = min(range(len(points)), key=lambda i: dist(last, points[i]))
        sorted_pts.append(points.pop(nearest_idx))
    return sorted_pts


def interpolate_path(points, num_points):
    unique_points = []
    if len(points) > 0:
        unique_points.append(points[0])
        for p in points[1:]:
            if dist(p, unique_points[-1]) > 0.1:
                unique_points.append(p)

    unique_points = sort_nearest_neighbor(unique_points)
    x = np.array([p[0] for p in unique_points])
    y = np.array([p[1] for p in unique_points])

    gap = dist((x[0], y[0]), (x[-1], y[-1]))
    is_closed = gap < 2.0

    try:
        tck, u = splprep([x, y], s=0, k=min(3, len(x) - 1), per=is_closed)
        u_new = np.linspace(0, 1, num_points, endpoint=not is_closed)
        new_points = splev(u_new, tck)
        return list(zip(new_points[0], new_points[1]))
    except:
        return unique_points[:num_points]


def transform_to_qmk_space(x, y, geo_min_x, geo_width, geo_min_y, geo_height):
    norm_x = (x - geo_min_x) / geo_width
    norm_y = (y - geo_min_y) / geo_height

    if FLIP_X_AXIS: norm_x = 1.0 - norm_x
    if FLIP_Y_AXIS: norm_y = 1.0 - norm_y

    target_w = QMK_MAX_X - QMK_MIN_X
    target_h = QMK_MAX_Y - QMK_MIN_Y

    if PRESERVE_ASPECT_RATIO:
        scale_x = target_w / geo_width
        scale_y = target_h / geo_height
        final_scale = min(scale_x, scale_y)

        scaled_w = geo_width * final_scale
        scaled_h = geo_height * final_scale

        x_offset = QMK_MIN_X + (target_w - scaled_w) / 2
        y_offset = QMK_MIN_Y + (target_h - scaled_h) / 2

        qx = (norm_x * geo_width) * final_scale + x_offset
        qy = (norm_y * geo_height) * final_scale + y_offset
        qy = QMK_MAX_Y - (qy - QMK_MIN_Y)
    else:
        qx = QMK_MIN_X + (norm_x * target_w)
        qy = QMK_MAX_Y - (norm_y * target_h)

    return (qx, qy)


# --- EXECUTION ---

doc = ezdxf.readfile(FILENAME)
msp = doc.modelspace()
raw_segments = []
for e in msp.query('LINE ARC SPLINE LWPOLYLINE CIRCLE'):
    pts = get_points_from_entity(e)
    if len(pts) > 1: raw_segments.append(pts)

full_paths = join_segments(raw_segments, tolerance=JOIN_TOLERANCE)

all_geometry_x, all_geometry_y = [], []
path_data = []

for p in full_paths:
    length = sum(dist(p[i], p[i + 1]) for i in range(len(p) - 1))
    path_data.append((length, p))
    for pt in p:
        all_geometry_x.append(pt[0]);
        all_geometry_y.append(pt[1])

path_data.sort(key=lambda x: x[0], reverse=True)
min_x, max_x = min(all_geometry_x), max(all_geometry_x)
min_y, max_y = min(all_geometry_y), max(all_geometry_y)
geo_width = max_x - min_x
geo_height = max_y - min_y

target_loop = path_data[TARGET_PATH_INDEX][1] if len(path_data) > TARGET_PATH_INDEX else path_data[0][1]

led_positions = interpolate_path(target_loop, NUM_LEDS)

# --- APPLY REVERSE ---
if REVERSE_DIRECTION:
    led_positions.reverse()

if AUTO_FIND_NOTCH:
    cx = sum(p[0] for p in led_positions) / len(led_positions)
    cy = sum(p[1] for p in led_positions) / len(led_positions)
    distances = [math.hypot(p[0] - cx, p[1] - cy) for p in led_positions]
    notch_index = np.argmin(distances)
    led_positions = led_positions[notch_index:] + led_positions[:notch_index]

if MANUAL_ROTATION != 0:
    led_positions = led_positions[MANUAL_ROTATION:] + led_positions[:MANUAL_ROTATION]

qmk_leds = []
final_xs, final_ys = [], []

for x, y in led_positions:
    qx, qy = transform_to_qmk_space(x, y, min_x, geo_width, min_y, geo_height)
    qmk_leds.append((qx, qy))
    final_xs.append(qx);
    final_ys.append(qy)

# --- STATS ---
print(f"Generated {len(qmk_leds)} LEDs. Reversed: {REVERSE_DIRECTION}")
print(f"X Bounds: {QMK_MIN_X}-{QMK_MAX_X} | Used: {min(final_xs):.1f}-{max(final_xs):.1f}")
print(f"Y Bounds: {QMK_MIN_Y}-{QMK_MAX_Y} | Used: {min(final_ys):.1f}-{max(final_ys):.1f}")

# --- VISUALIZATION ---
if VISUALIZE:
    plt.figure(figsize=(10, 10))
    for i, (length, p) in enumerate(path_data):
        px_list, py_list = [], []
        for x, y in p:
            qx, qy = transform_to_qmk_space(x, y, min_x, geo_width, min_y, geo_height)
            px_list.append(qx);
            py_list.append(qy)
        plt.plot(px_list, py_list, 'k-', alpha=0.3, linewidth=1)

    lx, ly = zip(*qmk_leds)
    plt.scatter(lx, ly, c=range(len(lx)), cmap='hsv', s=50, zorder=10)
    plt.plot(lx[0], ly[0], 'rx', markersize=15, markeredgewidth=3)
    plt.text(lx[0], ly[0] - 12, "START", color='red', fontweight='bold', ha='center')

    # Draw Arrow to show direction
    plt.arrow(lx[0], ly[0], lx[5] - lx[0], ly[5] - ly[0],
              head_width=5, color='black', zorder=20, label="Flow Direction")

    plt.plot([QMK_MIN_X, QMK_MAX_X, QMK_MAX_X, QMK_MIN_X, QMK_MIN_X],
             [QMK_MIN_Y, QMK_MIN_Y, QMK_MAX_Y, QMK_MAX_Y, QMK_MIN_Y], 'b--', label="Safe Zone")

    plt.title(f"Reversed: {REVERSE_DIRECTION} | Bounds: {QMK_MAX_X}x{QMK_MAX_Y}")
    plt.gca().set_aspect('equal', adjustable='box')
    plt.grid(True)
    plt.legend()
    plt.show()

print("\n// --- COPY TO KEYBOARD.C ---")
print("led_config_t g_led_config = {")
print("    { { NO_LED } },")
print("    {")
for i, (x, y) in enumerate(qmk_leds):
    print(f"        {{ {int(x):3}, {int(y):3} }}, // {i}")
print("    },")
print("    {")
for i in range(len(qmk_leds)):
    print(f"        LED_FLAG_UNDERGLOW,")
print("    }")
print("};")