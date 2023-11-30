import pandas as pd
import matplotlib.pyplot as plt
from numpy import std

#############################################################
################## Help Function and Init ###################
def getTimesAndStd(filename: str) -> tuple[list[list[float]], list[float]]:
    # tuple[0] = [times_T2, times_T4, ...], times_TX = [x1, x2, x3, x4, x5]
    # tuple[1] = [ecart_type_T2, écart_type_T4, ...]
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
    Times_per_threads = Res
    Std_per_threads = [std(measures) for measures in Res]

    return Times_per_threads, Std_per_threads

def getMeanAndStd(filename: str) -> tuple[list[list[float]], list[float]]:
    # tuple[0] = [times_T2, times_T4, ...], times_TX = [x1, x2, x3, x4, x5]
    # tuple[1] = [ecart_type_T2, écart_type_T4, ...]
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


figure, axis = plt.subplots(1, 3)


# ==================================================================
# ================( 3. Reader-Writer Time Analysis )================
# ==================================================================

Le_times_per_threads, Le_std_per_threads = getTimesAndStd("data/lect_writer.csv")

Le2_times_per_threads, Le2_std_per_threads = getTimesAndStd("data/lect_writer2.csv")

Le_mean_per_threads, Le_std_per_threads = getMeanAndStd("data/lect_writer2.csv")

Le2_mean_per_threads, Le2_std_per_threads = getMeanAndStd("data/lect_writer2.csv")

axis[0].set_title("R - W: Box Plot")
axis[0].set_xlabel("Nombre de threads")

box1 = axis[0].boxplot(Le_times_per_threads, positions=[0.8, 1.8, 2.8, 3.8, 4.8, 5.8], widths=0.35, patch_artist=True)

box2 = axis[0].boxplot(Le2_times_per_threads, positions=[1.2, 2.2, 3.2, 4.2, 5.2, 6.2], widths=0.35, patch_artist=True)

for patch in box1['boxes']:
    patch.set_facecolor('blue')

# Set colors for the second set of boxplots
for patch in box2['boxes']:
    patch.set_facecolor('orange')

axis[0].set_xticks([1, 2, 3, 4, 5, 6], ['2', '4', '8', '16', '32', '64'])

axis[0].legend(["Using Default Sem (left box)", "Using our Sem (right box)"])

axis[0].set_ylabel("Moyenne sur 5 tests [s]", color = (0, 0, 0, 1))
axis[0].grid(linestyle='--', alpha=0.5)

axis[0].set_facecolor("lavender")

axis[1].set_title("R - W: Error Bar Plot: représentation de l'écart-type")

axis[1].errorbar(["2", "4", "8", "16", "32", "64"], Le_std_per_threads, yerr=Le_std_per_threads, color = (0.8, 0.2, 0.2, 0.5))

axis[1].errorbar(["2", "4", "8", "16", "32", "64"], Le2_std_per_threads, yerr=Le2_std_per_threads, color = (0, 0, 0, 0.4))

axis[1].legend(["Using Default Sem", "Using our Sem"])
axis[1].set_xlabel("Nombre de threads")
axis[1].set_ylabel("Écart-Type", color = (0, 0, 0, 1))
axis[1].grid(linestyle='--', alpha=0.5)

axis[1].set_facecolor("lavender")

axis[2].set_title("R - W: Bar Plot")
axis[2].set_xlabel("Nombre de threads")

axis[2].bar(["2", "4", "8", "16", "32", "64"], Le_mean_per_threads, color = (0.8, 0.2, 0.2, 0.5))

axis[2].bar(["2", "4", "8", "16", "32", "64"], Le2_mean_per_threads, color = (0, 0, 0, 0.4))



axis[2].legend(["Using Default Sem", "Using our Sem"])

axis[2].set_ylabel("Moyenne sur 5 tests [s]", color = (0, 0, 0, 1))
axis[2].grid(linestyle='--', alpha=0.5)

axis[2].set_facecolor("lavender")


# ==================================================================
# ===================( 4. Ploting Settings )========================
# ==================================================================


# Each y should start at 0
axis[0].set_ylim(bottom=0)  
axis[1].set_ylim(bottom=0)  
axis[2].set_ylim(bottom=0)  

fig = plt.gcf()
fig.set_size_inches(25, 14, forward=True)

plt.grid(linestyle='--', alpha=0.5)
# plt.subplots_adjust(top=0.937,
#                     bottom=0.097,
#                     left=0.03,
#                     right=0.982,
#                     hspace=0.2,
#                     wspace=0.242)

plt.show()

