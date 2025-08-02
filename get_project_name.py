# get_project_name.py

import re

def get_project_name(cmake_file="CMakeLists.txt"):
    try:
        with open(cmake_file, 'r') as f:
            content = f.read()
            match = re.search(r'project\s*\(\s*([^\s\)]+)', content, re.IGNORECASE)
            return match.group(1) if match else "project_name_not_found"
    except FileNotFoundError:
        return "project_name_not_found"
