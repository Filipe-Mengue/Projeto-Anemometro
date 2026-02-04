# Anemômetro Digital - Projeto de Instrumentação Meteorológica

## 📋 Visão Geral
Este projeto consiste no desenvolvimento completo (mecânico, eletrônico e software) de um anemômetro digital para medição de velocidade do vento. O objetivo principal foi criar um instrumento funcional, com foco no tratamento do sinal ruidoso e na calibração precisa dos dados obtidos.

**Principais Desafios Superados:**
* Design e construção da estrutura mecânica para minimizar atrito.
* Condicionamento do sinal elétrico gerado pelo sensor.
* Definição da curva de calibração para garantir confiabilidade metrológica.

## 📄 Documentação Técnica (Relatório)
Para detalhes aprofundados sobre os cálculos físicos, esquemáticos elétricos e metodologia de testes, acesse o relatório

👉 **[Clique aqui para visualizar o Relatório Técnico (PDF)](Relatório_Anemometro.pdf)**
*(Certifique-se de que o arquivo PDF esteja na pasta 'docs' do repositório)*

---

## ⚙️ Detalhes Técnicos

### 1. Hardware e Eletrônica
* **Microcontrolador:** Arduino
* **Sensor de Rotação:** Infravermelho ITR8102
* **Condicionamento de Sinal:** Circuito desenvolvido para filtrar ruídos (debounce/filtro passa-baixa) e garantir a leitura limpa dos pulsos gerados pela rotação das pás.

### 2. Design Mecânico
A estrutura foi projetada visando aerodinâmica e baixo atrito.
* **Materiais:**  Materiais Reciclados
* **Mecânica:** Uso de rolamentos para garantir fluidez no movimento rotacional mesmo em baixas velocidades de vento.


## 📸 Galeria
![Foto do Anemômetro]
<img width="978" height="714" alt="image" src="https://github.com/user-attachments/assets/151f768d-52fb-44ce-bed2-3c915920735e" />

![Esquema] 
<img width="517" height="268" alt="image" src="https://github.com/user-attachments/assets/6f1cfa05-286f-4653-b7d2-f0fb70c6aac8" />



---
*Projeto desenvolvido como parte da disciplina de Instrumentação Eletrônica do curso de Engenharia de Computação da UERGS.*
