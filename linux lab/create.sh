
dir="mydir"

for file in "$@"; do
    if test -f $file; then
        echo "File $file exists in the current directory"
    else
        if test -d $dir; then
            echo "Directory $dir exists in the current directory"
            cd $dir
            echo "Number of files in mydir " $(ls | wc -w)
        else
            echo "$dir does not exist"
            mkdir $dir
            cd $dir
            for f1 in "$@"; do
                touch $f1
            done
            cd ..
            exit
        fi
    fi
done
