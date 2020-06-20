import pandas as pd
import sys


def main(argv_list):
    if len(argv_list) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
    else:
        with open(argv_list[2]) as f:
            case = f.read()  # targeted DNA sequance (string)
            db = pd.read_csv(argv_list[1])  # database
            strs_checked = db.columns.values.tolist()[1:]  # all checked STRs (column names)
            dna_dict = {}  # dictionary used to store repeated times of all checked STRs

            for i in strs_checked:
                dna_dict[i] = check(i, case)

            for row in range(len(db)):
                matched = 0
                for key in dna_dict:
                    if db[key][row] == dna_dict[key]:
                        matched += 1

                if matched == len(strs_checked):
                    print(db["name"][row])
                    break
                elif row == len(db) - 1:
                    print("No match")


def check(STR, DNA):
    DNA_len = len(DNA)
    STR_len = len(STR)
    rt_list = []  # store all repeated times of checked STR in this DNA
    for i in range(DNA_len):
        if DNA[i: i + STR_len] == STR:
            rt = 1
            # check the following each sequance of checked STR's length, break counting repeated times once the continuity stops.
            for j in range(i + STR_len, DNA_len, STR_len):
                if DNA[j: j + STR_len] == STR:
                    rt += 1
                else:
                    break
            rt_list.append(rt)

    # return the largest repeated time
    if len(rt_list) != 0:
        return max(rt_list)
    else:
        return 0


main(sys.argv)