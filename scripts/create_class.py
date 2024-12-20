import os


def standard_path(input_string):
    return input_string.replace("\\", "/")


def create_class(class_name, base_path="", sub_path=""):
    include_dir = os.path.join(base_path, "includes")
    include_dir = os.path.join(include_dir, sub_path)
    src_dir = os.path.join(base_path, "src")
    src_dir = os.path.join(src_dir, sub_path)

    # File paths
    header_file = os.path.join(include_dir, f"{class_name}.h")
    source_file = os.path.join(src_dir, f"{class_name}.cpp")

    # Create directories if they don't exist
    os.makedirs(include_dir, exist_ok=True)
    os.makedirs(src_dir, exist_ok=True)

    # Boilerplate code for .h
    header_boilerplate = f"""#ifndef {class_name.upper()}_H
#define {class_name.upper()}_H

class {class_name} {{
public:
    {class_name}();
    ~{class_name}();
}};

#endif
"""

    # Boilerplate code for .cpp
    source_boilerplate = f"""#include "../../{standard_path(header_file)}"
#include <iostream>

{class_name}::{class_name}() {{
    // Constructor implementation
}}

{class_name}::~{class_name}() {{
    // Destructor implementation
}}

"""

    # Write header file
    if not os.path.exists(header_file):
        with open(header_file, "w") as h_file:
            h_file.write(header_boilerplate)
        print(f"Created {header_file}")
    else:
        print(f"{header_file} already exists!")

    # Write source file
    if not os.path.exists(source_file):
        with open(source_file, "w") as cpp_file:
            cpp_file.write(source_boilerplate)
        print(f"Created {source_file}")
    else:
        print(f"{source_file} already exists!")

if __name__ == "__main__":
    class_name = input("Enter class name: ")
    base_path = input("Enter project base path (or leave empty for current directory): ").strip()
    sub_dir = input("Enter sub directory path: ").strip()
    create_class(class_name, base_path or ".", sub_dir)
