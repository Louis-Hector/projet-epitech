##
## EPITECH PROJECT, 2026
## G-CNA-400-LIL-4-1-interstonar-7
## File description:
## file_global
##

from core import tomllib, sys, math, GRAVITATION, ROCK, sub_vectors, add_vectors, mult_vectors, move_celestial

def parse_toml_global(file):
    tab = []
    try:
        with open(file, 'rb') as f:
            blocs = tomllib.load(f)
        if (blocs is None):
            sys.exit(84)
        for elem in blocs.get('body'):
            name = elem.get('name')
            position = elem.get('position') 
            direction = elem.get('direction')
            mass = elem.get('mass')
            radius = elem.get('radius')
            if (name is None or position is None or direction is None or mass is None or radius is None):
                sys.exit(84)
            celestial = {'name' : elem.get('name'),
                        'position' : {'x' : float(position['x']), 'y' : float(position['y']), 'z' : float(position['z'])},
                        'direction' : {'x' : float(direction['x']), 'y' : float(direction['y']), 'z' : float(direction['z'])},
                        'mass' : float(mass),
                        'radius' : float(radius)
            }
            tab.append(celestial)
    except (ValueError, TypeError, KeyError, PermissionError, FileNotFoundError):
        sys.exit(84)
    return tab

def new_celestial(celest1, celest2):
    new_celest = {}
    new_celest['name'] = '-'.join(sorted([celest1['name'], celest2['name']]))
    new_celest['mass'] = celest1['mass'] + celest2['mass']
    volume_sum = (4/3 * math.pi * (celest1['radius'] ** 3)) + (4/3 * math.pi * (celest2['radius']  ** 3))
    new_celest['radius'] = math.cbrt((volume_sum / (4/3)) / math.pi)
    vx1 = celest1['direction']['x']
    vy1 = celest1['direction']['y']
    vz1 = celest1['direction']['z']
    speed_norm1 = math.sqrt(vx1 * vx1 + vy1 * vy1 + vz1 * vz1)
    vx2 = celest2['direction']['x']
    vy2 = celest2['direction']['y']
    vz2 = celest2['direction']['z']
    speed_norm2 = math.sqrt(vx2 * vx2 + vy2 * vy2 + vz2 * vz2)
    speed_total = speed_norm1 + speed_norm2
    if speed_total == 0:
        new_celest['position'] = {'x': (celest1['position']['x'] + celest2['position']['x']) / 2.0, 'y': (celest1['position']['y'] + celest2['position']['y']) / 2.0, 'z': (celest1['position']['z'] + celest2['position']['z']) / 2.0}
    else:
        new_celest['position'] = {'x': (celest1['position']['x'] * speed_norm1 + celest2['position']['x'] * speed_norm2) / speed_total, 'y': (celest1['position']['y'] * speed_norm1 + celest2['position']['y'] * speed_norm2) / speed_total, 'z': (celest1['position']['z'] * speed_norm1 + celest2['position']['z'] * speed_norm2) / speed_total}
    new_celest['direction'] = {'x': (celest1['direction']['x'] * celest1['mass'] + celest2['direction']['x'] * celest2['mass']) / new_celest['mass'], 'y': (celest1['direction']['y'] * celest1['mass'] + celest2['direction']['y'] * celest2['mass']) / new_celest['mass'], 'z': (celest1['direction']['z'] * celest1['mass'] + celest2['direction']['z'] * celest2['mass']) / new_celest['mass']}
    return new_celest

def check_merge_clestials(infos):
    for i in range(len(infos)):
        for j in range(i + 1, len(infos)):
            celest1 = infos[i]
            celest2 = infos[j]
            position_celest_1 = [celest1['position']['x'], celest1['position']['y'], celest1['position']['z']]
            position_celest_2 = [celest2['position']['x'], celest2['position']['y'], celest2['position']['z']]
            vect_celest = sub_vectors(position_celest_1, position_celest_2)
            distance = math.sqrt(vect_celest[0] ** 2 + vect_celest[1] ** 2 + vect_celest[2] ** 2)
            if (distance <= celest1['radius'] + celest2['radius']):
                k = new_celestial(celest1, celest2)
                infos.pop(j)
                infos.poo(i)
                infos.append(k)
                return
    return infos


def launch_global(file, time, tab_pi_vi):
    infos = parse_toml_global(file)
    position = [tab_pi_vi[0], tab_pi_vi[1], tab_pi_vi[2]]
    velocity = [tab_pi_vi[3], tab_pi_vi[4], tab_pi_vi[5]]
    print("Rock coordinates (x y z) are:")
    for t in range(0, 1001):
        print(f"t = {t}: ({position[0]:,.0f} {position[1]:,.0f} {position[2]:,.0f})")
        total = [0.0, 0.0, 0.0]
        for celestial in infos:
            vecteur_dict = [celestial['position']['x'], celestial['position']['y'], celestial['position']['z']]
            sub_vect = sub_vectors(vecteur_dict, position)
            distance = math.sqrt(sub_vect[0] ** 2 + sub_vect[1] ** 2 + sub_vect[2] ** 2)
            if distance <= celestial['radius']:
                print(f"Collision between rock and {celestial['name']}\n\nMission success")
                return
            if (distance == 0.0):
                continue
            direct = [sub_vect[0] / distance, sub_vect[1] / distance, sub_vect[2] / distance]
            force = GRAVITATION * ROCK * celestial['mass'] / (distance ** 2)
            total = add_vectors(total, mult_vectors(direct, force))
        new_m = [total[0] / ROCK, total[1] / ROCK, total[2] / ROCK]
        position = add_vectors(position, mult_vectors(velocity, time))
        velocity = add_vectors(velocity, mult_vectors(new_m, time))
        move_celestial(infos, time)
    infos = check_merge_clestials(infos)
    print("\nMission failure")
    return 0