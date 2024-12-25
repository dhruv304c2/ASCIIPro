
import os


def rename_class_globally(old_class_name, new_class_name, base_path="."):
    # Rename relevant files and update class name in all files
    for root, _, files in os.walk(base_path):
        for file in files:
            file_path = os.path.join(root, file)

            # Update class name in all relevant files before renaming
            if file.endswith((".cpp", ".h", ".hpp", ".c", ".cc", ".inl")):  # Add extensions as needed
                update_class_name_in_file(file_path, old_class_name, new_class_name)

            # Check if the file is a .cpp or .h file and rename if needed
            if file == f"{old_class_name}.cpp" or file == f"{old_class_name}.h":
                old_file_path = os.path.join(root, file)
                new_file_name = file.replace(old_class_name, new_class_name)
                new_file_path = os.path.join(root, new_file_name)

                os.rename(old_file_path, new_file_path)
                print(f"Renamed file: {old_file_path} -> {new_file_path}")


def update_class_name_in_file(file_path, old_class_name, new_class_name):
    """Update the class name in the file content."""
    try:
        with open(file_path, "r") as file:
            content = file.read()

        updated_content = content.replace(old_class_name, new_class_name)

        if content != updated_content:  # Check if any replacements were made
            with open(file_path, "w") as file:
                file.write(updated_content)
            print(f"Updated class name in: {file_path}")
    except Exception as e:
        print(f"Error processing file {file_path}: {e}")


if __name__ == "__main__":
    old_class_name = input("Enter the old class name: ").strip()
    new_class_name = input("Enter the new class name: ").strip()
    base_path = input("Enter project base path (or leave empty for current directory): ").strip()
    rename_class_globally(old_class_name, new_class_name, base_path or ".")
