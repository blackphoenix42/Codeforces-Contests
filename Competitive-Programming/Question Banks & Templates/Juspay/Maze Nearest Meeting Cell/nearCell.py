testCASES = int(input())
# testCASES=1
for case_number in range(testCASES):
    meshsize = input()

    mesh = input()
    # mesh='4 4 1 4 13 8 8 8 0 8 14 9 15 11 -1 10 15 22 22 22 22 22 21'
    det = input()
    # det='9 2'

    mesh = [int(x) for x in mesh.split()]
    det = [int(x) for x in det.split()]

    n1 = det[0]
    n2 = det[1]

    n1path = []
    n2path = []

    for i in range(len(mesh)):
        if not n1path:
            n1path.append(mesh[n1])
        else:
            n1path.append(mesh[n1path[i-1]])

        if not n2path:
            n2path.append(mesh[n2])
        else:
            n2path.append(mesh[n2path[i-1]])

    nearestList = []
    try:
        for x in n1path:
            nearestList.append(n2path.index(x))
        NEAREST_NODE = n2path[min(nearestList)]
    except Exception as e:
        NEAREST_NODE = -1

    # print(n1path,n2path)
    print(NEAREST_NODE)
