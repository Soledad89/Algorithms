folder=`pwd`
dirlist=`ls .`
for dir in $dirlist; do
	f=$folder/$dir
	for i in `find $f -name "*.h" -or -name "*.cpp"`; do
		iconv -f "gbk" -t "utf-8" < $i > $i"tmp"
		mv $i"tmp" $i
		echo $i;
	done
done
echo "done!"
