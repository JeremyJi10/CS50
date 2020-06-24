import sys
from cs50 import SQL

def main(argv_list):
    try:
        # uppercase the housename so that the query will be case-insensitive
        house_upper = argv_list[1].upper()
        db = SQL("sqlite:///students.db")
        #get all needed rows of data (a list of dict)
        results = db.execute(f"SELECT * FROM students WHERE UPPER(house) = '{house_upper}' ORDER BY last ASC, first ASC;")
        
        for row in results:
            if row['middle'] == None:
                print(f"{row['first']} {row['last']}, born {row['birth']}")
            else:
                print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")
    except:
        print("Usage: python roster.py HouseName")
    
    
main(sys.argv)