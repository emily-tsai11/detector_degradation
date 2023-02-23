#!/bin/zsh

echo Remaking all histograms...
for dir in *; do
  if [ -d "$dir" ]; then
    rootFile=$(echo "$dir" | awk -F '_f' '{print $1}' )
    cd $dir
    echo -----------------------------------------------------------------------
    if [[ $rootFile == *"TRK2026D88PU200MB2_noTPStubCut"* ]]; then
      time ./../makeHists.csh $rootFile.root
    fi
    cd ..
  fi
done
echo -----------------------------------------------------------------------
echo Finished!
