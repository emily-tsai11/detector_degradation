#!/bin/zsh

echo Remaking all histograms...
for dir in *; do
  if [ -d "$dir" ]; then
    rootFile=$(echo "$dir" | awk -F '_f' '{print $1}' )
    cd $dir
    echo -----------------------------------------------------------------------
    time ./../makeHists.csh $rootFile.root
    cd ..
  fi
done
echo -----------------------------------------------------------------------
echo Finished!
