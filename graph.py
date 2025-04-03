import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import tkinter as tk
from tkinter import ttk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Load stock data
df = pd.read_csv("stocks.csv")

# Calculate investment, profit/loss
df["Investment"] = df["Buy Price"] * df["Quantity"]
df["Current Value"] = df["Current Price"] * df["Quantity"]
df["Profit/Loss"] = df["Current Value"] - df["Investment"]
df["Change %"] = ((df["Current Price"] - df["Buy Price"]) / df["Buy Price"]) * 100

# Create main Tkinter window
root = tk.Tk()
root.title("Stock Portfolio Analysis")
root.state("zoomed")  

# **LEFT SIDE: STOCK TABLE**
frame_table = tk.Frame(root)
frame_table.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

# Create table with treeview
tree = ttk.Treeview(frame_table, columns=list(df.columns), show="headings")
for col in df.columns:
    tree.heading(col, text=col)
    tree.column(col, width=120)

# Insert data into table
for i, row in df.iterrows():
    tree.insert("", tk.END, values=list(row))

tree.pack(fill=tk.BOTH, expand=True)

# **RIGHT SIDE: GRAPHS**
frame_graphs = tk.Frame(root)
frame_graphs.pack(side=tk.RIGHT, fill=tk.BOTH, expand=True)

fig, axes = plt.subplots(1, 2, figsize=(10, 4))  # Create two side-by-side plots

# **Profit/Loss Bar Chart**
sns.barplot(x=df["Stock"], y=df["Profit/Loss"], palette=["red" if x < 0 else "green" for x in df["Profit/Loss"]], ax=axes[0])
axes[0].axhline(0, color="black", linewidth=1.2)
axes[0].set_title("Profit/Loss Distribution")
axes[0].set_ylabel("Profit/Loss (₹)")
axes[0].set_xlabel("Stock")
axes[0].tick_params(axis="x", rotation=45)

# **Investment Pie Chart**
axes[1].pie(df["Investment"], labels=df["Stock"], autopct="%1.1f%%", startangle=90, colors=sns.color_palette("pastel"))
axes[1].set_title("Investment Distribution")

# Embed Matplotlib graph into Tkinter
canvas = FigureCanvasTkAgg(fig, master=frame_graphs)
canvas.draw()
canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

# Run Tkinter main loop
root.mainloop()
