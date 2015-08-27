for i in `find . -name "*.h" -or -name "*.cpp"`; do
	iconv -f "gbk" -t "utf-8" < $i > $i"tmp"
	mv $i"tmp" $i
done
echo "done!"
