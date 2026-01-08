# reading the root file and plotting the histograms
import uproot
import matplotlib.pyplot as plt

file = uproot.open("build/output0.root")

# Accessing the first ntuple
ntuple1 = file["Hits;1"]

# plotting the edep vs copyNo 
edep = ntuple1["Edep"].array()
copyNo = ntuple1["CopyNo"].array()

# adding the total energy deposition on specific copyNo
energy_deposition = {}
for cn, ed in zip(copyNo, edep):
    if cn in energy_deposition:
        energy_deposition[cn] += ed
    else:
        energy_deposition[cn] = ed
copyNo_unique = list(energy_deposition.keys())
edep_total = list(energy_deposition.values())


plt.figure(figsize=(10,6))
plt.bar(copyNo_unique, edep_total, color='green', alpha=0.7)
# plt.plot(copyNo_unique, poisson(np.array(copyNo_unique), lamb_fit), 'r-', label=f'Poisson fit (lambda={lamb_fit:.2f})')
plt.xlabel('Copy Number')
plt.ylabel('Total Energy Deposition (MeV)')
plt.title('Total Energy Deposition vs Copy Number')
# plt.legend()
# plt.savefig("total_edep_vs_copyNo.png")
plt.show()

plt.figure(figsize=(10,6))
plt.scatter(copyNo, edep, c='blue', alpha=0.5)
plt.colorbar(label='Counts')
plt.xlabel('Copy Number')
plt.ylabel('Energy Deposition (MeV)')
plt.title('Energy Deposition vs Copy Number')
# plt.savefig("edep_vs_copyNo.png")
plt.show()