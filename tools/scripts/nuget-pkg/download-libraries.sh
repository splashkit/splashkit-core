#!/bin/bash

# See comments at end about adding libraries to NuGet package

# Set the GitHub repository URL
repo_url="https://github.com/splashkit/skm.git"

# Set the branch name
branch="master"

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

# TODO: Add the following comment lines to SplashKitSDK.csproj (with further testing)
# <PlatformTarget>AnyCPU</PlatformTarget>

# <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|AnyCPU'">
#     <DebugType>portable</DebugType>
# </PropertyGroup>

# <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|AnyCPU'">
#     <DebugType>portable</DebugType>
# </PropertyGroup>

# <ItemGroup>
#     <Content Include=".\Libraries\win64\*.dll">
#         <Pack>true</Pack>
#         <PackagePath>lib\$(TargetFramework)</PackagePath>
#         <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
#         <PackageCopyToOutput>true</PackageCopyToOutput>
#         <Link>%(FileName)%(Extension)</Link>
#     </Content>
#     <Content Include=".\Libraries\macos\libSplashKit.dylib">
#         <Pack>true</Pack>
#         <PackagePath>lib\$(TargetFramework)</PackagePath>
#         <CopyToOutputDirectory>PreserveNewest</CopyToOutputDirectory>
#         <PackageCopyToOutput>true</PackageCopyToOutput>
#         <Link>%(FileName)%(Extension)</Link>
#     </Content>
# </ItemGroup>
