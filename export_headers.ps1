rm -r material
md -force .\material\
md -force .\material\lib
$toCopy = gci .\components\* -exclude *_p.h, *_internal.h -include  *.h
Copy-Item $toCopy -Destination .\material
$toCopy = gci .\components\lib\* -exclude *_p.h, *_internal.h -include  *.h
Copy-Item $toCopy -Destination .\material\lib