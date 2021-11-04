
# Suppression de toutes les données des simulations précédentes 
cd ../out
rm position*
rm velocity*
rm acceleration*
cd ..

# Execution du fichier de pointage des paramètres de la simulation
python ./simulation_parameters.py

# Execution du script de génération de la distribution de masses
cd ./tools/
python ./distribution_generator.py
cd ..

# Compilation du code 
cd ./src/
g++ -std=c++11 main.cpp -o main.o
./main.o

