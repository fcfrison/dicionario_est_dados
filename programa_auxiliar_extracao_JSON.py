import json


#######################################################################################
##################################   OBSERVAÇÃO   #####################################
#######################################################################################

# OBJETIVO DO ALGORITMO: Fazer a extração dos dados de um arquivo em formato JSON, modelá-lo e grava-lo em 
# um arquivo de texto com formato 'txt'.


# O arquivo em formato JSON contendo as palavras e suas definicoes foi retirado desse perfil no Github 
# https://github.com/matthewreagan/WebstersEnglishDictionary#dictionary_compactjson
# Para ser mais específico, o arquivo se chama ""dictionary_compact.json" e pode ser extraído aqui:
# https://github.com/matthewreagan/WebstersEnglishDictionary/blob/master/dictionary_compact.json



#######################################################################################
################################  INICIA PROGRAMA #####################################
#######################################################################################

# Abrindo arquivo JSON.
english_dictionary = json.load(open('dictionary_compact.json'))

# Função para remover caracteres não ASCII.
def remove_non_ascii_1(text):
	return ''.join([i if ord(i) < 128 else '' for i in text])

# Modelando os dados para que possam ser facilmente lidos pela linguagem C.
lista=[]
for word, definition in english_dictionary.items():
	word = remove_non_ascii_1(word)
	word.replace('\n\n',' ')
	definition = remove_non_ascii_1(definition)
	definition=definition.replace('\n\n',' ')
	definition=definition.replace('@','')
	lista.append(word+'@'+definition)

# Abrindo arquivo de texto para gravação.
textfile = open("retorno.txt", "w")

# Gravando dados modelados em arquivo de texto.
for element in lista:
    textfile.write(element + "\n")

# Fechando arquivo de texto aberto. 
textfile.close()