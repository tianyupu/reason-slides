# This should be run from the root of the repository
curr_dir=$(basename $(pwd))
if [[ $curr_dir != "reason-slides" ]]; then
    echo "Please run this script from the root of the repository. Exiting"
    exit 1
fi

# Make sure we're on the master branch
git checkout master

# Compile re -> js and bundle assets
yarn build && yarn webpack:production

# Go to gh-pages branch
git checkout gh-pages

# The bundled stuff will be in build/. Move them out into the
# top-level, since we're hosting statically
cp -R build/ .

# Find any changes to tracked files and commit and push them
git st -s | grep ' [MD]' | cut -d' ' -f 3 | xargs git add
git commit -m "Update gh-pages"
git push

# Upload to surge
surge . reason-slides.surge.sh

# Go back to master
git checkout master

# Finished! :)
echo "Finished deploying to surge and GH pages ✨"