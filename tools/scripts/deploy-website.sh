#!/bin/bash

# Website Redeployment Script
# Purpose: Automate the redeployment of the website after api.json is regenerated.

# Configuration
## If you face any issues with the script, like $'\r': command not found
## try running the following command in your terminal:
## sudo apt-get install dos2unix
## dos2unix deploy-website.sh
## chmod +x deploy-website.sh
## ./deploy-website.sh

USER="splashkit" 
SK_ROOT="$(cd ../../ && pwd)"
SK_GENERATED="$SK_ROOT/generated"
REPO_NAME="splashkit.io-starlight"
SK_OUT="$SK_ROOT/out"
NETLIFY_SITE_ID="YOUR_NETLIFY_SITE_ID"
BRANCH=""

# Prompt user for branch selection
echo "Choose a branch to make changes:"
echo "1. Development (https://github.com/$USER/$REPO_NAME/tree/development)"
echo "2. Production (default) (https://github.com/$USER/$REPO_NAME/tree/master)"
read -p "Enter the number (1 or 2): " branch_choice

# Validate and set branch
if [ "$branch_choice" == "1" ]; then
    BRANCH="development"
elif [ "$branch_choice" == "2" ]; then
    BRANCH="master"
else
    echo "Invalid choice. Using default branch (master)."
    BRANCH="development"
fi

# Clone the website repository with the specified branch
git clone --branch "$BRANCH" "https://github.com/$USER/$REPO_NAME.git" "$SK_OUT/$REPO_NAME"

# Copy the api.json to the website repository
cp "$SK_GENERATED/docs/api.json" "$SK_OUT/$REPO_NAME/scripts/json-files/"

# Navigate to the website repository
cd "$SK_OUT/$REPO_NAME" || exit

# Checkout the selected branch
git checkout "$BRANCH" || exit

# Commit and push changes
git add scripts/json-files/api.json
git commit -m "Update api.json"
git push origin "$BRANCH"

# Remove the cloned repository
cd "$SK_OUT" || exit
rm -rf "$REPO_NAME"

# Trigger Netlify deployment
# Uncomment the line below if you want to trigger Netlify deployment
# curl -X POST -d {} "https://api.netlify.com/build_hooks/$NETLIFY_SITE_ID"
