##
## EPITECH PROJECT, 2026
## G-CNA-400-LIL-4-1-interstonar-7
## File description:
## file_local
##

from core import tomllib, sys, math, sub_vectors, add_vectors, mult_vectors, move_celestial

def parse_toml_local(file):
    tab = []
    count = {}
    try:
        with open(file, 'rb') as f:  
            blocs = tomllib.load(f)   
        if (blocs is None):
            sys.exit(84)
        for elem in blocs.get('body'):
            scene = {}
            name = elem.get('name')
            _type = elem.get('type')
            position = elem.get('position')
            if (_type is None or position is None):
                sys.exit(84)
            count[_type] = count.get(_type, 0) + 1
            if (name is not None):
                scene['name'] = name
            else:
                scene['name'] = _type.upper() + '_' + str(count[_type])
            scene['type'] = _type
            scene['position'] = {'x' : int(position['x']), 'y' : int(position['y']), 'z' : int(position['z'])}
            if (_type == 'sphere' or _type == 'cylinder'):
                if (elem.get('radius') is None):
                    sys.exit(84)
                scene['radius'] = float(elem.get('radius'))
            if (_type == 'cylinder'):
                if (elem.get('height') is not None):
                    scene['height'] = int(elem.get('height'))
                else:
                    scene['height'] = None
            if (_type == 'box'):
                sides = elem.get('sides')
                if (sides is None):
                    sys.exit(84)
                scene['sides'] = {'x' : int(sides['x']), 'y' : int(sides['y']), 'z' : int(sides['z'])}
            if (_type == 'torus'):
                inner_radius = (elem.get('inner_radius'))
                outer_radius = (elem.get('outer_radius'))
                if (inner_radius is None or outer_radius is None):
                    sys.exit(84)
                scene['inner_radius'] = float(inner_radius)
                scene['outer_radius'] = float(outer_radius)
            tab.append(scene)
    except (KeyError, ValueError, TypeError, PermissionError, FileNotFoundError):
        sys.exit(84)
    return tab


def print_forms(infos, position, velocity):
    print(f"Rock thrown at the point ({position[0]:.2f}, {position[1]:.2f}, {position[2]:.2f}) and parallel to the vector ({velocity[0]:.2f}, {velocity[1]:.2f}, {velocity[2]:.2f})")       
    for elem in infos:
        form = elem.get('type')
        position = elem.get('position')
        if (form == "sphere"):
            print(f"Sphere of radius {elem.get('radius'):.2f} at position ({position['x']:.2f}, {position['y']:.2f}, {position['z']:.2f})")
        if (form == "cylinder"):   
            height = elem.get('height')
            if (height != None):
                print(f"Cylinder of radius {elem.get('radius'):.2f} and height {height:.2f} at position ({position['x']:.2f}, {position['y']:.2f}, {position['z']:.2f})")
            else:
                print(f"Cylinder of radius {elem.get('radius'):.2f} and infinite height at position ({position['x']:.2f}, {position['y']:.2f}, {position['z']:.2f})")
        if (form == "box"):  
            sides = elem.get('sides')
            print(f"Box of dimensions ({sides['x']:.2f}, {sides['y']:.2f}, {sides['z']:.2f}) at position ({position['x']:.2f}, {position['y']:.2f}, {position['z']:.2f})")
        if (form == "torus"):
            print(f"Torus of inner radius {elem.get('inner_radius'):.2f} and outer radius {elem.get('outer_radius'):.2f} at position ({position['x']:.2f}, {position['y']:.2f}, {position['z']:.2f})")
    print()
    
    
def calculate_sdf_sphere(position, elem):
    position_form = elem.get('position')
    vector_dict = [position_form['x'], position_form['y'], position_form['z']]
    sub_vect = sub_vectors(vector_dict,  position)
    distance = math.sqrt(sub_vect[0] ** 2 + sub_vect[1] ** 2 + sub_vect[2] ** 2) - elem.get('radius')
    return distance
    
def calculate_sdf_cylinder(position, elem):
    position_form = elem.get('position')
    vector_dict = [position_form['x'], position_form['y'], position_form['z']]
    radius = elem.get('radius')
    height = elem.get('height')
    distancexy = math.sqrt((position[0] - vector_dict[0]) ** 2 + (position[1] - vector_dict[1]) ** 2) - radius
    if height is None:
        return distancexy
    distancey = abs(position[2] - vector_dict[2]) - height / 2
    outside = math.sqrt(max(distancexy, 0.0) ** 2 + max(distancey, 0.0) ** 2)
    inside = min(max(distancexy, distancey), 0.0)
    return outside + inside


def calculate_sdf_box(position, elem):
    position_form = elem.get('position')
    vector_dict = [position_form['x'], position_form['y'], position_form['z']]
    sides = elem.get('sides')
    sides_dict = [sides['x'], sides['y'], sides['z']]
    x = abs(position[0] - vector_dict[0]) - sides_dict[0] / 2
    y = abs(position[1] - vector_dict[1]) - sides_dict[1] / 2
    z = abs(position[2] - vector_dict[2]) - sides_dict[2] / 2
    outside = math.sqrt(max(x, 0.0) ** 2 + max(y, 0.0) ** 2 + max(z, 0.0) ** 2)
    inside = min(max(x, y, z), 0.0)
    return outside + inside


def calculate_sdf_torus(position, elem):
    position_form = elem.get('position')
    vector_dict = [position_form['x'], position_form['y'], position_form['z']]
    inner_radius = elem.get('inner_radius') 
    outer_radius = elem.get('outer_radius')
    distance_inner = math.sqrt((position[0] - vector_dict[0]) ** 2 + (position[1] - vector_dict[1]) ** 2) - inner_radius
    return math.sqrt(distance_inner ** 2 + (position[2] - vector_dict[2]) ** 2) - outer_radius

def launch_local(file, time, tab_pi_vi):
    infos = parse_toml_local(file)
    position = [tab_pi_vi[0], tab_pi_vi[1], tab_pi_vi[2]]
    velocity = [tab_pi_vi[3], tab_pi_vi[4], tab_pi_vi[5]]
    vect_norm = math.sqrt(velocity[0]**2 + velocity[1]**2 + velocity[2]**2)
    if (vect_norm == 0):
        return 84
    direction = [velocity[0] / vect_norm, velocity[1] / vect_norm, velocity[2] / vect_norm]
    print_forms(infos, position, velocity)
    for t in range(1, 1001):
        distance_min = float("inf")
        close_form = None
        for elem in infos:
            form = elem.get('type')
            if form == 'sphere':
                distance = calculate_sdf_sphere(position, elem)
            elif form == 'cylinder':
                distance = calculate_sdf_cylinder(position, elem)
            elif form == 'box':
                distance = calculate_sdf_box(position, elem)
            elif form == 'torus':
                distance = calculate_sdf_torus(position, elem)
            else:
                continue
            if distance < distance_min:
                distance_min = distance
                close_form = elem
        position = add_vectors(position, mult_vectors(direction, distance_min))
        if distance_min > 1000:
            print(f"Step {t}: ({position[0]:.2f}, {position[1]:.2f}, {position[2]:.2f})")
            print("\nResult: Out of scene")
            return 0
        if distance_min <= 0.1:
            print(f"Step {t}: ({position[0]:.2f}, {position[1]:.2f}, {position[2]:.2f})")
            print(f"\nResult: Intersection with {close_form.get('name')}")
            return 0
        print(f"Step {t}: ({position[0]:.2f}, {position[1]:.2f}, {position[2]:.2f})")
    print("\nResult: Steps limit reached")
    return 0