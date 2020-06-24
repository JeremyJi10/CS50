import sys
import csv
from cs50 import SQL

def main(argv_list):
    try:
        # connect the database
        db = SQL("sqlite:///students.db")

        with open(argv_list[1], 'r') as f:
            all_data = csv.reader(f)
            #skip the header in following loops and create a variable called index to record and update id
            header = next(all_data)
            index = 0
            for row in all_data:
                NameList = row[0].split(' ')
                #check whether this student has middle name or not
                if len(NameList) == 2:
                    db.execute(f"INSERT INTO students (id, first, middle, last, house, birth) VALUES ({index},'{NameList[0]}',NULL,'{NameList[1]}','{row[1]}',{row[2]});")
                else:
                    db.execute(f"INSERT INTO students (id, first, middle, last, house, birth) VALUES ({index},'{NameList[0]}','{NameList[1]}','{NameList[2]}','{row[1]}',{row[2]});")
                index += 1
    except:
        print("Usage: python import.py data.csv")

main(sys.argv)
