from argparse import ArgumentParser

parser = ArgumentParser()

parser.add_argument("key1", type=str)
parser.add_argument("key2", type=str)

args = parser.parse_args()

def calc_weight(k1, k2):
    w = 0
    for i in range(0,4):
        diff = abs(int(k1[i])-int(k2[i]))
        w += min(diff, 10-diff)
    return w

k1 = args.key1
k2 = args.key2

print(calc_weight(k1,k2))