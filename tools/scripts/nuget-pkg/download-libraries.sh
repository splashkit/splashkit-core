#!/bin/bash

# Set the GitHub repository URL
repo_url="https://github.com/splashkit/skm.git"

# Set the branch name
branch="develop"

# Set the folders to download
folders=("lib/macos" "lib/win64")

# Create the destination directory if it doesn't exist
mkdir -p ./Libraries

# Loop through the folders and download them
for folder in "${folders[@]}"
do
    # Clone the repository into a temporary directory
    temp_dir=$(mktemp -d)
    git clone --branch "${branch}" --depth 1 "${repo_url}" "${temp_dir}"

    # Copy the folder to the destination directory
    cp -r "${temp_dir}/${folder}" "./Libraries/"

    # Remove the temporary directory
    rm -rf "${temp_dir}"
done