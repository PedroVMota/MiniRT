#!/bin/bash
dirs=("src/")

# Initialize the file count
file_count=0

# Iterate through each directory
for dir in "${dirs[@]}"; do
  # Use find to locate all the .c files in the specified directory and its subdirectories
  c_files=$(find "$dir" -type f -name "*.c")

  # Iterate through each found file
  for file in $c_files; do
    # Print the file path
    echo -n "$file "

    # Increment the file counter
    ((file_count++))

    # Check if 4 files have been printed, then end the line with '\'
    if ((file_count % 4 == 0)); then
      echo -n "\\"
    fi

    # Move to the next line if 4 files have been printed
    if ((file_count % 4 == 0)); then
      echo ""
    fi
  done
done

# Add a newline at the end of the output if the last line is incomplete
if ((file_count % 4 != 0)); then
  echo ""
fi