set arg=%1
set filename=%~nx1
msdf-atlas-gen.exe -font %1 -type msdf -format png -size 16 -imageout "output/"%filename%".atlas.png" -json "output/"%filename%".metadata.json"
