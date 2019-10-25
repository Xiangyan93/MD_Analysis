# MD_analysis
This is a code used to analyze the trajectory of MD simulation.
Only GRO trajectory is available.

1. Calculate radial distribution function(RDF)  
```
cd analysis  
g++ -o rdf rdf.cpp  
./rdf traj.gro MO0 MO1 0.01 3  
```
arguments: trajectory file, center molecule name, surround molecule name, distance increasement, cutoff.  
output: rdf.txt.  
Details:  
the molecule name is defined in the topol file. The code read the infomation in the gro file.  
There is an artifact of RDF beyond half of the box length because the image partile is not considered in the code.  

2. Calculate diffusion constant using Green-Kubo method.  
```
cd analysis  
g++ -o diff diffusion.cpp  
./diff traj.gro  
```
output: V-acf-[].txt(autocorrelation function) diff-[].txt(integral diffusion constant).  
[] = all type of molecules. For each type of molecule, its autocorrelation function and diffusion constant will be calculated.  
System: Consider all particles together.  
