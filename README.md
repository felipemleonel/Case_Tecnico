# Case Técnico 

Este repositório apresenta a resolução das questões propostas utilizando o **Zephyr RTOS**. A validação foi realizada por meio de simulação com o **QEMU** emulando um microcontrolador **ARM Cortex-M3**.

## 📁 Estrutura do Projeto

A implementação está organizada de forma modular, com arquivos `.c` e `.h` separados por funcionalidade:

- Cada **task** possui seu próprio conjunto de arquivos.
- Os arquivos restantes tratam da configuração de **timers** e da **comunicação entre tasks**.

## Q1

Para resolver a problemática proposta, foram implementadas quatro tasks distintas. A primeira é responsável por gerar valores de temperatura aleatórios, variando entre 26 °C e 26,5 °C. A segunda realiza a amostragem desses valores, enquanto a terceira envia os dados ao terminal. A quarta task é dedicada ao setup do sistema, permitindo configurar parâmetros como n_sample, freq_sample e freq_pkg. O sequenciamento entre as tasks foi controlado por semáforos: inicialmente, apenas a task de setup é permitida, e somente após sua conclusão as demais podem ser executadas. Além disso, semáforos em conjunto com timers foram utilizados para controlar as frequências de amostragem e de envio dos pacotes. A comunicação entre as tasks de amostragem e envio é realizada por meio de uma fila, garantindo a integridade dos dados mesmo quando as frequências de amostragem e envio são diferentes.

## Q2

Neste problema, foram criadas apenas duas tasks: uma responsável por gerar valores aleatórios e outra encarregada de enviar os dados ao terminal. As frequências de geração e envio dos dados são controladas da mesma forma que na Q1, por meio de semáforos em conjunto com timers.

## Q3

Neste problema, foram criadas três tasks: uma responsável por simular o sistema de lançamento, outra para simular o míssil e uma terceira para realizar a contagem do tempo de autodestruição. A task do sistema de lançamento segue a seguinte rotina: realiza o lançamento, entra em sleep por 3,5 segundos, executa testes de conexão com o míssil e inicia o envio dos dados de guiagem. A task do míssil tem sua rotina pautada em responder mensagens do sistema de lançamento e se autodestrói caso receba uma flag da task de contagem de tempo. Esta última, por sua vez, entra em sleep por 3 segundos após o início dos testes de comunicação e, se a conexão não for estabelecida nesse intervalo, envia uma flag de autodestruição ao míssil. Vale destacar que o sleep inicial de 3,5 segundos foi utilizado para sincronizar a contagem com o tempo de espera do sistema de lançamento.
