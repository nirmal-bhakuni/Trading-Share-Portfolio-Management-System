import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import tkinter as tk
from tkinter import ttk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

df = pd.read_csv("stocks.csv")

df["Investment"] = df["Buy Price"] * df["Quantity"]
df["Current Value"] = df["Current Price"] * df["Quantity"]
df["Profit/Loss"] = df["Current Value"] - df["Investment"]
df["Change %"] = ((df["Current Price"] - df["Buy Price"]) / df["Buy Price"]) * 100

root = tk.Tk()
root.title("Stock Portfolio Analysis")
root.state("zoomed")  

frame_table = tk.Frame(root)
frame_table.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

tree = ttk.Treeview(frame_table, columns=list(df.columns), show="headings")
for col in df.columns:
    tree.heading(col, text=col)
    tree.column(col, width=120)

for i, row in df.iterrows():
    tree.insert("", tk.END, values=list(row))

tree.pack(fill=tk.BOTH, expand=True)

frame_graphs = tk.Frame(root)
frame_graphs.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)

fig, axes = plt.subplots(1, 2, figsize=(10, 4))  # Create two side-by-side plots

sns.barplot(x=df["Stock"], y=df["Profit/Loss"], palette=["red" if x < 0 else "green" for x in df["Profit/Loss"]], ax=axes[0])
axes[0].axhline(0, color="black", linewidth=1.2)
axes[0].set_title("Profit/Loss Distribution")
axes[0].set_ylabel("Profit/Loss (₹)")
axes[0].set_xlabel("Stock")
axes[0].tick_params(axis="x", rotation=45)

axes[1].pie(df["Investment"], labels=df["Stock"], autopct="%1.1f%%", startangle=90, colors=sns.color_palette("pastel"))
axes[1].set_title("Investment Distribution")

canvas = FigureCanvasTkAgg(fig, master=frame_graphs)
canvas.draw()
canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

root.mainloop()
