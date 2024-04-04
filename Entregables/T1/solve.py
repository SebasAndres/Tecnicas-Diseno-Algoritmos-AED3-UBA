# Imprime la solucion en pantalla
def printSolution(best_team):
    res = ['' for _ in range(10)]
    for name, (pos, _, _) in best_team.items():
        res[pos] = name    

    # separar en ataque y defensa
    attack = res[:5]
    defense = res[5:]

    # orden alfabetico
    attack.sort()
    defense.sort()
 
    print(f"({', '.join(attack)})")
    print(f"({', '.join(defense)})")

# Dado un equipo devuelve el puntaje en ataque y defensa
def getTeamScore(team:dict) -> tuple:
    attack_score = 0
    defense_score = 0
    for pos, attack_skill, def_skill in team.values():
        if pos < 5:
            attack_score += attack_skill
        else:
            defense_score += def_skill
    return attack_score, defense_score

# Dada una solucion parcial, determina si podria extenderse a una solucion optima
def couldExtendToSolution(bestPossibleAttack,     # mejor ataque posible
                        currTeam,               # diccionario de jugadores en el equipo actual
                        ) -> bool: 
    # la idea es que si el equipo actual tiene un ataque menor al mejor ataque, no es un buen candidato
    att_sc, _ = getTeamScore(currTeam)
    return att_sc >= bestPossibleAttack

# Devuelve los primeros 5 jugadores con mas ataque sin incluir los que empatan al final
def getFirstPlayers(casePlayers) -> list:
    sortedByAttack = sorted(casePlayers, key=lambda x: x[1], reverse=True)
    res = dict()
    i = 0
    while (i<6):
        p_name, p_att, p_def = sortedByAttack[i]

        if sortedByAttack[i][1] != sortedByAttack[i+1][1]:
            res[p_name] = (len(res), p_att, p_def)
        else:
            repetidosConsecutivos = 0
            while (sortedByAttack[i+repetidosConsecutivos][1] == sortedByAttack[i+repetidosConsecutivos+1][1]):
                repetidosConsecutivos += 1
            if (i+repetidosConsecutivos+1 < 5):
                for w in range(repetidosConsecutivos):
                    p_name, p_att, p_def = sortedByAttack[i+w]
                    res[p_name] = (len(res), p_att, p_def)
            break
        i+=1
    return res

# Resuelve el problema con backtracking
def solve(casePlayers,                  # lista de jugadores                                :: list[(name, att, def)]
          _currTeam,                    # diccionario de jugadores en el equipo actual      :: dict{name: (position, att, def)}
          best_attack,                  # mejor ataque actual       
          best_defense,                 # mejor defensa actual
          best_possible_attack          # mejor ataque posible
          ):      
    
    # para evitar aliasing
    global case_best_team
    currTeam = _currTeam.copy()

    # caso base
    if len(currTeam) == 5:

        # agrego los otros jugadores restantes
        for p_name, p_atts, p_defs in casePlayers:
            if p_name not in currTeam:
                currTeam[p_name] = (len(currTeam), p_atts, p_defs)

        # calculo el puntaje del equipo
        t_attack_score, t_defense_score = getTeamScore(currTeam)

        # reglas de decision
        if t_attack_score > best_attack:
            best_attack = t_attack_score
            best_defense = t_defense_score
            case_best_team = currTeam.copy()
        elif t_attack_score == best_attack:
            if t_defense_score > best_defense:
                best_attack = t_attack_score
                best_defense = t_defense_score
                case_best_team = currTeam.copy()
            elif t_defense_score == best_defense:
                # regla lexicografica
                pass
            pass
        return 
    
    # caso recursivo
    for p_name, p_atts, p_defs in casePlayers:
        # valido que no este ya en el equipo
        if p_name not in currTeam:
            # agregar jugador al equipo            
            currTeam[p_name] = (len(currTeam), p_atts, p_defs)
            # poda por optimalidad
            if len(currTeam)<5 or couldExtendToSolution(best_possible_attack, currTeam):
                solve(casePlayers, currTeam, best_attack, best_defense, best_possible_attack)
            # sacar jugador del equipo
            del currTeam[p_name]

if __name__ == "__main__":
    # input
    # T = input()
    # cases = [[] for _ in range(T)]
    # for i in range(T):
    #     name, atts, defs = input().split(" ")
    #     atts = int(atts)
    #     defs = int(defs)
    #     cases[i].append((name, atts, defs))

    cases = [
        [
            ("sameezahur", 20, 21),
            ("sohelh", 18, 9),
            ("jaan", 17, 86),
            ("sidky", 16, 36),
            ("shamim", 16, 18),
            ("shadowcoder", 12, 9),
            ("muntasir", 13, 4),
            ("brokenarrow", 16, 16),
            ("emotionalblind", 16, 12),
            ("tanaeem", 20, 97)
        ]
    ]

    # output
    c = 0
    for casePlayers in cases:
        print("Case " + str(c+1) + ":")

        # inicializar variables
        case_best_team = {}
        bestPossibleAttack = sum([x[1] for x in sorted(casePlayers, key=lambda x: x[1], reverse=True)[:5]])
        
        # resolver el caso
        firstPlayers = getFirstPlayers(casePlayers)
        solve(casePlayers, firstPlayers, 0, 0, bestPossibleAttack)           

        # imprimir solucion
        printSolution(case_best_team)      
