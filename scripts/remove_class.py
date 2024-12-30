import os


def find_and_remove_class(class_name, base_path="."):
    # Directories to search for .cpp and .h files
    src_dir = os.path.join(base_path, "src")
    include_dir = os.path.join(base_path, "include")

    # Search and remove .cpp and .h files recursively
    remove_file_in_subdirs(src_dir, f"{class_name}.cpp")
    remove_file_in_subdirs(include_dir, f"{class_name}.h")

    # Clean up empty subdirectories
    cleanup_empty_dirs(src_dir)
    cleanup_empty_dirs(include_dir)


def remove_file_in_subdirs(directory, filename):
    """Recursively search for and remove a file in subdirectories."""
    for root, _, files in os.walk(directory):
        if filename in files:
            file_path = os.path.join(root, filename)
            os.remove(file_path)
            print(f"Removed {file_path}")
            return  # Stop after finding the file
    print(f"{filename} not found in {directory}.")


def cleanup_empty_dirs(directory):
    """Recursively remove empty subdirectories."""
    for root, dirs, _ in os.walk(directory, topdown=False):
        for dir_name in dirs:
            dir_path = os.path.join(root, dir_name)
            if not os.listdir(dir_path):
                os.rmdir(dir_path)
                print(f"Removed empty directory: {dir_path}")


if __name__ == "__main__":
    class_name = input("Enter the class name to remove: ").strip()
    base_path = input("Enter project base path (or leave empty for current directory): ").strip()
    find_and_remove_class(class_name, base_path or ".")
