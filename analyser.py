import pandas as pd
import matplotlib.pyplot as plt
from numpy import std

# Open file
philo_data = pd.read_csv("data/philosophe.csv")

# Retrieve all data from tests
t2 = philo_data.iloc[0].tolist()[1:]
t4 = philo_data.iloc[1].tolist()[1:]
t8 = philo_data.iloc[2].tolist()[1:]
t16 = philo_data.iloc[3].tolist()[1:]
t32 = philo_data.iloc[4].tolist()[1:]
t64 = philo_data.iloc[5].tolist()[1:]

lists = [t2, t4, t8, t16, t32, t64]

# Compute data used in plots
mean_per_threads = [sum(measures)/len(measures) for measures in lists]
std_per_threads = [std(measures) for measures in lists]

# subplots
figure, axis = plt.subplots(2)

# Philosopher problem
axis[0].bar(["2", "4", "8", "16", "32", "64"], mean_per_threads)
axis[0].set_title("Problème des Philosophes")
axis[0].grid(linestyle='--', alpha=0.5)
axis[0].set_facecolor("lavender")

axis[1].scatter(["2", "4", "8", "16", "32", "64"], std_per_threads)
axis[1].set_facecolor("lavender")

# Plot titles
plt.setp(axis[0], ylabel="Moyenne de 5 tests [s]")
plt.setp(axis[1], ylabel="Écart-type")

plt.xlabel("Nombre de threads")

plt.style.use('Solarize_Light2')
plt.grid(linestyle='--', alpha=0.5)
plt.show()
