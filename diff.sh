PATH="maptool/*"
for f in $PATH
do
	diff maptool2/$(basename $f) $f
done
