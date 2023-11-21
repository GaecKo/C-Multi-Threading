import pandas as pd
import matplotlib.pyplot as plt
from numpy import std

# ==================================================================
# ====================( 1. Philo Time Analysis )====================
# ==================================================================

# Open file
philo_data = pd.read_csv("data/philosophe.csv")

# Retrieve all data from tests, without number of threads
PhT2 = philo_data.iloc[0].tolist()[1:]
PhT4 = philo_data.iloc[1].tolist()[1:]
PhT8 = philo_data.iloc[2].tolist()[1:]
PhT16 = philo_data.iloc[3].tolist()[1:]
PhT32 = philo_data.iloc[4].tolist()[1:]
PhT64 = philo_data.iloc[5].tolist()[1:]

PhRes = [PhT2, PhT4, PhT8, PhT16, PhT32, PhT64]

# Compute data used in plots
Ph_mean_per_threads = [sum(measures)/len(measures) for measures in PhRes]
Ph_std_per_threads = [std(measures) for measures in PhRes]

# ==================================================================
# ==================( 2. Prod-Conso Time Analysis )=================
# ==================================================================

# Open file
prod_data = pd.read_csv("data/prod_conso.csv")

# Retrieve all data from tests, without number of threads
PrT2 = prod_data.iloc[0].tolist()[1:]
PrT4 = prod_data.iloc[1].tolist()[1:]
PrT8 = prod_data.iloc[2].tolist()[1:]
PrT16 = prod_data.iloc[3].tolist()[1:]
PrT32 = prod_data.iloc[4].tolist()[1:]
PrT64 = prod_data.iloc[5].tolist()[1:]

PrRes = [PrT2, PrT4, PrT8, PrT16, PrT32, PrT64]

# Compute data used in plots
Pr_mean_per_threads = [sum(measures)/len(measures) for measures in PrRes]
Pr_std_per_threads = [std(measures) for measures in PrRes]

# ==================================================================
# ================( 3. Reader-Writer Time Analysis )================
# ==================================================================

# Open file
lect_data = pd.read_csv("data/lect_writer.csv")

# Retrieve all data from tests, without number of threads
LeT2 = lect_data.iloc[0].tolist()[1:]
LeT4 = lect_data.iloc[1].tolist()[1:]
LeT8 = lect_data.iloc[2].tolist()[1:]
LeT16 = lect_data.iloc[3].tolist()[1:]
LeT32 = lect_data.iloc[4].tolist()[1:]
LeT64 = lect_data.iloc[5].tolist()[1:]

LeRes = [LeT2, LeT4, LeT8, LeT16, LeT32, LeT64]

# Compute data used in plots
Le_mean_per_threads = [sum(measures)/len(measures) for measures in LeRes]
Le_std_per_threads = [std(measures) for measures in LeRes]

# ==================================================================
# ========================( 4. Ploting )============================
# ==================================================================

figure, axis = plt.subplots(1, 3)

############################################################
#################### Philosopher problem ####################

axis[0].set_title("Problème des Philosophes")
axis[0].set_xlabel("Nombre de threads")

axis[0].bar(["2", "4", "8", "16", "32", "64"], Ph_mean_per_threads, color = (0, 0, 0, 0.4))

axis[0].set_ylabel("Moyenne sur 5 tests [s]", color = (0, 0, 0, 1))
axis[0].grid(linestyle='--', alpha=0.5)

axis[0].set_facecolor("lavender")

ax0 = axis[0].twinx()
ax0.set_ylabel('Écart-type', color="tab:blue")
ax0.scatter(["2", "4", "8", "16", "32", "64"], Ph_std_per_threads)
ax0.tick_params(axis='y', color="tab:blue")

############################################################
#################### Prod-Conso problem ####################

axis[1].set_title("Problème des Producteurs - Consommateurs")
axis[1].set_xlabel("Nombre de threads")

axis[1].bar(["2", "4", "8", "16", "32", "64"], Pr_mean_per_threads, color = (0, 0, 0, 0.4))

axis[1].set_ylabel("Moyenne sur 5 tests [s]", color = (0, 0, 0, 1))
axis[1].grid(linestyle='--', alpha=0.5)

axis[1].set_facecolor("lavender")

ax1 = axis[1].twinx()
ax1.set_ylabel('Écart-type', color="tab:blue")
ax1.scatter(["2", "4", "8", "16", "32", "64"], Pr_std_per_threads)
ax1.tick_params(axis='y', color="tab:blue")

############################################################
#################### Lect-Writer problem ###################

axis[2].set_title("Problème des Lecteurs - Écrivaints")
axis[2].set_xlabel("Nombre de threads")

axis[2].bar(["2", "4", "8", "16", "32", "64"], Le_mean_per_threads, color = (0, 0, 0, 0.4))

axis[2].set_ylabel("Moyenne sur 5 tests [s]", color = (0, 0, 0, 1))
axis[2].grid(linestyle='--', alpha=0.5)

axis[2].set_facecolor("lavender")

ax2 = axis[2].twinx()
ax2.set_ylabel('Écart-type', color="tab:blue")
ax2.scatter(["2", "4", "8", "16", "32", "64"], Le_std_per_threads)
ax2.tick_params(axis='y', color="tab:blue")

############################################################
######################## Resizing ##########################

fig = plt.gcf()
fig.set_size_inches(18, 6, forward=True)

plt.grid(linestyle='--', alpha=0.5)
plt.subplots_adjust(top=0.937,
                    bottom=0.097,
                    left=0.03,
                    right=0.957,
                    hspace=0.2,
                    wspace=0.272)

plt.show()
