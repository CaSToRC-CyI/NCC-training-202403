#!/bin/bash
#SBATCH -J fletcher32
#SBATCH -o f32.txt
#SBATCH -e f32.err
#SBATCH -p gpu
#SBATCH -A edu19
#SBATCH --reservation=edu19
#SBATCH -t 00:02:00
#SBATCH -n 1
#SBATCH -N 1
#SBATCH --ntasks-per-node=1

date +"%T.%6N"
srun ./f32 /nvme/scratch/edu19/data/03.txt
date +"%T.%6N"
