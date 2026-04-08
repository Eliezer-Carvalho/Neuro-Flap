@echo off


call C:\Users\eliez\emsdk\emsdk_env.bat

emcc NeuroFlap.c -o index.html ^
-I "C:/Users/eliez/raylib/src" ^
-L . ^
-lraylib ^
--preload-file "C:/Users/eliez/Desktop/Neuro-Flap/Imagens/flappybird1.png@C:/Users/eliez/Desktop/Neuro-Flap/Imagens/flappybird1.png" ^
--preload-file "C:/Users/eliez/Desktop/Neuro-Flap/Imagens/flappybird2.png@C:/Users/eliez/Desktop/Neuro-Flap/Imagens/flappybird2.png" ^
-s EXPORTED_FUNCTIONS="['_main', '_JUMP', '_GAME_ON']" ^
-s USE_GLFW=3 ^
-s WASM=1 ^
-s ALLOW_MEMORY_GROWTH=1 ^
-s ASYNCIFY

pause




::Passo 1 - Download via git clone do Emscripten | Aceder á pasta onde ficou instalado | install latest | activate latest | emsdk_env.bat
::Passo 2 - Download via git clone do RayLib | Aceder à pasta do Makefile (Por norma \src) | Alterar o Makefile - PLATFORM = PLATFORM_WEB | Com o env ativo - emmake make PLATFORM=PLATFORM_WEB |
::Passo 3 - Compilar com emcc como está neste ficheiro (Após o passo 2 vai ser gerado um ficheiro .a que é necessário e o ficheiro raylib.h também é necessário para compilar)

::A partir daqui, sempre que se for converter ficheiros novos para WASM é necessário ativar o ambiente e depois rodar o script (Já não é necessário rodar emmake make PLATFORM = PLATFORM_WEB)