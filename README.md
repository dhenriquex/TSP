# Problema do Caixeiro Viajante (TSP) em C

Este repositório contém um programa em C que resolve o Problema do Caixeiro Viajante (TSP) utilizando o método de Branch and Bound. O TSP é um problema clássico de otimização onde o objetivo é encontrar a rota mais curta que visita cada cidade exatamente uma vez e retorna à cidade inicial.


## Introdução
O Problema do Caixeiro Viajante (TSP) faz a seguinte pergunta: "Dada uma lista de cidades e as distâncias entre cada par de cidades, qual é a rota mais curta possível que visita cada cidade exatamente uma vez e retorna à cidade de origem?" Este problema é NP-difícil, o que significa que não há solução em tempo polinomial conhecida para ele.

## Como Funciona
Esta implementação usa o método de Branch and Bound para gerar todas as permutações possíveis de visitas às cidades e calcula a distância total para cada permutação. A rota mais curta é então determinada a partir dessas permutações. Embora esta abordagem seja simples e garanta encontrar a solução ótima, é computacionalmente cara e não adequada para grandes números de cidades.
