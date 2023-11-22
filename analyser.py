import pandas as pd
import matplotlib.pyplot as plt
from numpy import std

#############################################################
################## Help Function and Init ###################
def getMeanAndStd(filename: str) -> tuple[list[float], float]:
    # Open file
    data = pd.read_csv(filename)

    # Retrieve all data from tests, without number of threads
    T2 = data.iloc[0].tolist()[1:]
    T4 = data.iloc[1].tolist()[1:]
    T8 = data.iloc[2].tolist()[1:]
    T16 = data.iloc[3].tolist()[1:]
    T32 = data.iloc[4].tolist()[1:]
    T64 = data.iloc[5].tolist()[1:]

    Res = [T2, T4, T8, T16, T32, T64]

    # Compute data used in plots
    Mean_per_threads = [sum(measures)/len(measures) for measures in Res]
    Std_per_threads = [std(measures) for measures in Res]

    return Mean_per_threads, Std_per_threads

figure, axis = plt.subplots(1, 4)

# ==================================================================
# ====================( 1. Philo Time Analysis )====================
# ==================================================================

Ph_mean_per_threads, Ph_std_per_threads = getMeanAndStd("data/philosophe.csv")

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

# ==================================================================
# ==================( 2. Prod-Conso Time Analysis )=================
# ==================================================================

# Compute data used in plots
Pr_mean_per_threads, Pr_std_per_threads = getMeanAndStd("data/prod_conso.csv")

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

# ==================================================================
# ================( 3. Reader-Writer Time Analysis )================
# ==================================================================

Le_mean_per_threads, Le_std_per_threads = getMeanAndStd("data/lect_writer.csv")

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

# ==================================================================
# ================( 4. Test-and-Set Time Analysis )================
# ==================================================================

T_s_mean_per_threads, T_s_std_per_threads = getMeanAndStd("data/test_and_set.csv")

axis[3].set_title("Test-and-Set")
axis[3].set_xlabel("Nombre de threads")

axis[3].bar(["2", "4", "8", "16", "32", "64"], T_s_mean_per_threads, color = (0, 0, 0, 0.4))

axis[3].set_ylabel("Moyenne sur 5 tests [s]", color = (0, 0, 0, 1))
axis[3].grid(linestyle='--', alpha=0.5)

axis[3].set_facecolor("lavender")

ax3 = axis[3].twinx()
ax3.set_ylabel('Écart-type', color="tab:blue")
ax3.scatter(["2", "4", "8", "16", "32", "64"], T_s_std_per_threads)
ax3.tick_params(axis='y', color="tab:blue")

# ==================================================================
# ===================( 4. Ploting Settings )========================
# ==================================================================

fig = plt.gcf()
fig.set_size_inches(18, 6, forward=True)

plt.grid(linestyle='--', alpha=0.5)
plt.subplots_adjust(top=0.937,
                    bottom=0.097,
                    left=0.03,
                    right=0.957,
                    hspace=0.2,
                    wspace=0.412)

plt.show()
