cp -avx -f ../include/* ./Classes

srcPath="./Classes/src"

if [[ ! -d "$srcPath" ]]; then
	mkdir "$srcPath"
fi

cp -avx -f ../src/* "$srcPath"


pluginsPath="./Classes/plugins"

if [[ ! -d "$pluginsPath" ]]; then
	mkdir "$pluginsPath"
fi

cp -avx -f ../plugins/* "$pluginsPath"