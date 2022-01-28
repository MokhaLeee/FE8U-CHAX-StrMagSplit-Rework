base_dir=$(dirname "$(readlink -f "$0")")
source_rom="$base_dir/FE8U.gba"
target_rom="$base_dir/FE8-CHAX.gba"
ea_core="$base_dir/Tools/EventAssembler/ColorzCore.exe"
main_event="$base_dir/Main.event"

if [[ $1 == all ]]; then

	# Compile C
	cd "$base_dir/Wizardry"
	echo "===== Compiling C ====="
	make clean
	make lyn
	echo "Compile CHAX .. done!"

fi

if [[ $1 != quick ]]; then

	# Assembling Tables
	echo "===== Make C2EA ====="
	cd "$base_dir/GameData/Tables"
	rm *.event
	python3 c2ea.py ../FE8U.gba
	echo "Make Tables .. done!"

	# Assembling Text
	echo "===== Make Text ====="
	cd "$base_dir/Writans"
	rm InstallTextData.event
	python3 text-process-cn.py text_buildfile.txt InstallTextData.event TextDefinition.txt
	echo "Make Text .. done!"
fi


# Preparing ROM
cd "$base_dir"
echo "===== Copy ROM ====="
cp -f "$source_rom" "$target_rom"
echo "Copy Target ROM .. done!"

# Make Hack
cd "$base_dir"
echo "===== Make Hack ====="
"$ea_core" A FE8 "-input:$main_event" "-output:$target_rom"
echo "done!"