

build-app:
	@clang++ -std=c++20 app.cpp -o app
	./app

HTTP_ALL_CPP := $$(find ./http-server -name '*.cpp')

build-app-server:
	clang++ -std=c++20 $(HTTP_ALL_CPP) -o app-server
	#./app-server 8090