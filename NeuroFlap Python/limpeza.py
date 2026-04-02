import pandas as pd
import re

df = pd.read_csv("Tanh_Sigmoid.csv", header = None)

df.dropna(axis = 1, thresh = len(df) * 0.5, inplace = True)

#df.to_csv("Teste.csv", index = False)


df = df.replace(r"Fitness Indivíduo \d+ ->", "", regex = True)

df = df.replace(r"Indivíduo \d+", "", regex = True)

df = df [~df[0].str.contains(r"\|", na = False)]


df.to_csv('teste.csv', index = False)




with open("teste.csv", "r", encoding="utf-8") as f:
    linhas = f.readlines()

geracoes = {}  
geracao_atual = None

for linha in linhas:
    linha = linha.strip()
    
    
    if linha == "" or linha == '""' or linha == "''":
        continue
    
    
    if "Geração" in linha:
        geracao_atual = int(re.search(r"\d+", linha).group())
        geracoes[geracao_atual] = []
        continue
    
    
    if geracao_atual is not None:
        try:
            geracoes[geracao_atual].append(float(linha))
        except ValueError:
            
            pass


max_len = max(len(v) for v in geracoes.values())


df = pd.DataFrame({f"Geração {k}": v + [None]*(max_len - len(v)) for k, v in geracoes.items()})


df.to_csv("fitness_colunas.csv", index=False)






