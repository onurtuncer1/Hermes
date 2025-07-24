# get_project_name.py
import re
import sys

def get_project_name(cmake_file):
    try:
        with open(cmake_file, 'r') as f:
            content = f.read()
            match = re.search(r'project\((\w+)', content)
            if match:
                print(match.group(1))
            else:
                print("project_name_not_found")
    except FileNotFoundError:
        print("project_name_not_found")

if __name__ == "__main__":
    cmake_file = sys.argv[1] if len(sys.argv) > 1 else "CMakeLists.txt"
    get_project_name(cmake_file)
