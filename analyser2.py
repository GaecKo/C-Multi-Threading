import pandas as pd
import matplotlib.pyplot as plt
from numpy import std

#############################################################
################## Help Function and Init ###################
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

figure, axis = plt.subplots(2, 4)


# ==================================================================
# ====================( 1. Philo Time Analysis )====================
# ==================================================================

Ph_mean_per_threads, Ph_std_per_threads = getMeanAndStd("data/philosophe.csv")

Ph2_mean_per_threads, Ph2_std_per_threads = getMeanAndStd("data/philosophe2.csv")


axis[0, 0].set_title("Problème des Philosophes")
axis[0, 0].set_xlabel("Nombre de threads")

axis[0, 0].bar(["2", "4", "8", "16", "32", "64"], Ph_mean_per_threads, color = (0.8, 0.2, 0.2, 0.5))

axis[0, 0].bar(["2", "4", "8", "16", "32", "64"], Ph2_mean_per_threads, color = (0, 0, 0, 0.4))



axis[0, 0].legend(["Using Default Sem", "Using our Sem"])

axis[0, 0].set_ylabel("Moyenne sur 5 tests [s]", color = (0, 0, 0, 1))
axis[0, 0].grid(linestyle='--', alpha=0.5)

axis[0, 0].set_facecolor("lavender")



axis[1, 0].errorbar(["2", "4", "8", "16", "32", "64"], Ph_std_per_threads, yerr=Ph_std_per_threads, color = (0.8, 0.2, 0.2, 0.5))

axis[1, 0].errorbar(["2", "4", "8", "16", "32", "64"], Ph2_std_per_threads, yerr=Ph2_std_per_threads, color = (0, 0, 0, 0.4))

axis[1, 0].legend(["Using Default Sem", "Using our Sem"])
axis[1, 0].set_xlabel("Nombre de threads")
axis[1, 0].set_ylabel("Écart-Type", color = (0, 0, 0, 1))
axis[1, 0].grid(linestyle='--', alpha=0.5)

axis[1, 0].set_facecolor("lavender")


# ==================================================================
# ==================( 2. Prod-Conso Time Analysis )=================
# ==================================================================

Pr_mean_per_threads, Pr_std_per_threads = getMeanAndStd("data/prod_conso.csv")

Pr2_mean_per_threads, Pr2_std_per_threads = getMeanAndStd("data/prod_conso2.csv")


axis[0, 1].set_title("Problème des Producteurs - Consommateurs")
axis[0, 1].set_xlabel("Nombre de threads")

axis[0, 1].bar(["2", "4", "8", "16", "32", "64"], Pr_mean_per_threads, color = (0.8, 0.2, 0.2, 0.5))

axis[0, 1].bar(["2", "4", "8", "16", "32", "64"], Pr2_mean_per_threads, color = (0, 0, 0, 0.4))



axis[0, 1].legend(["Using Default Sem", "Using our Sem"])

axis[0, 1].set_ylabel("Moyenne sur 5 tests [s]", color = (0, 0, 0, 1))
axis[0, 1].grid(linestyle='--', alpha=0.5)

axis[0, 1].set_facecolor("lavender")



axis[1, 1].errorbar(["2", "4", "8", "16", "32", "64"], Pr_std_per_threads, yerr=Pr_std_per_threads, color = (0.8, 0.2, 0.2, 0.5))

axis[1, 1].errorbar(["2", "4", "8", "16", "32", "64"], Pr2_std_per_threads, yerr=Pr2_std_per_threads, color = (0, 0, 0, 0.4))

axis[1, 1].legend(["Using Default Sem", "Using our Sem"])
axis[1, 1].set_xlabel("Nombre de threads")
axis[1, 1].set_ylabel("Écart-Type", color = (0, 0, 0, 1))
axis[1, 1].grid(linestyle='--', alpha=0.5)

axis[1, 1].set_facecolor("lavender")


# ==================================================================
# ================( 3. Reader-Writer Time Analysis )================
# ==================================================================

Le_mean_per_threads, Le_std_per_threads = getMeanAndStd("data/lect_writer.csv")

Le2_mean_per_threads, Le2_std_per_threads = getMeanAndStd("data/lect_writer2.csv")


axis[0, 2].set_title("Problème des Lecteurs - Écrivains")
axis[0, 2].set_xlabel("Nombre de threads")

axis[0, 2].bar(["2", "4", "8", "16", "32", "64"], Le_mean_per_threads, color = (0.8, 0.2, 0.2, 0.5))

axis[0, 2].bar(["2", "4", "8", "16", "32", "64"], Le2_mean_per_threads, color = (0, 0, 0, 0.4))



axis[0, 2].legend(["Using Default Sem", "Using our Sem"])

axis[0, 2].set_ylabel("Moyenne sur 5 tests [s]", color = (0, 0, 0, 1))
axis[0, 2].grid(linestyle='--', alpha=0.5)

axis[0, 2].set_facecolor("lavender")



axis[1, 2].errorbar(["2", "4", "8", "16", "32", "64"], Le_std_per_threads, yerr=Le_std_per_threads, color = (0.8, 0.2, 0.2, 0.5))

axis[1, 2].errorbar(["2", "4", "8", "16", "32", "64"], Le2_std_per_threads, yerr=Le2_std_per_threads, color = (0, 0, 0, 0.4))

axis[1, 2].legend(["Using Default Sem", "Using our Sem"])
axis[1, 2].set_xlabel("Nombre de threads")
axis[1, 2].set_ylabel("Écart-Type", color = (0, 0, 0, 1))
axis[1, 2].grid(linestyle='--', alpha=0.5)

axis[1, 2].set_facecolor("lavender")


# ==================================================================
# ================( 4. Test-and-Set Time Analysis )================
# ==================================================================

T_s_mean_per_threads, T_s_std_per_threads = getMeanAndStd("data/test_and_set.csv")

T_T_s_mean_per_threads, T_T_s_std_per_threads = getMeanAndStd("data/test_and_test_and_set.csv")


axis[0, 3].set_title("Test-and-set / Test-and-test-and-set")
axis[0, 3].set_xlabel("Nombre de threads")

axis[0, 3].bar(["2", "4", "8", "16", "32", "64"], T_s_mean_per_threads, color = (0.8, 0.2, 0.2, 0.5))

axis[0, 3].bar(["2", "4", "8", "16", "32", "64"], T_T_s_mean_per_threads, color = (0, 0, 0, 0.4))



axis[0, 3].legend(["Test-and-Set", "Test-and-Test-and-Set"])

axis[0, 3].set_ylabel("Moyenne sur 5 tests [s]", color = (0, 0, 0, 1))
axis[0, 3].grid(linestyle='--', alpha=0.5)

axis[0, 3].set_facecolor("lavender")



axis[1, 3].errorbar(["2", "4", "8", "16", "32", "64"], T_s_std_per_threads, yerr=T_s_std_per_threads, color = (0.8, 0.2, 0.2, 0.5))

axis[1, 3].errorbar(["2", "4", "8", "16", "32", "64"], T_T_s_std_per_threads, yerr=T_T_s_std_per_threads, color = (0, 0, 0, 0.4))

axis[1, 3].legend(["Test-and-Set", "Test-and-Test-and-Set"])
axis[1, 3].set_xlabel("Nombre de threads")
axis[1, 3].set_ylabel("Écart-Type", color = (0, 0, 0, 1))
axis[1, 3].grid(linestyle='--', alpha=0.5)

axis[1, 3].set_facecolor("lavender")


# ==================================================================
# ===================( 4. Ploting Settings )========================
# ==================================================================

fig = plt.gcf()
fig.set_size_inches(18, 12, forward=True)

plt.grid(linestyle='--', alpha=0.5)
plt.subplots_adjust(top=0.937,
                    bottom=0.097,
                    left=0.03,
                    right=0.957,
                    hspace=0.2,
                    wspace=0.412)

plt.show()
