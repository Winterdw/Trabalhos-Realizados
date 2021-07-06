function submeter_dados(){
	nomes[iterador]=document.getElementById("nome").value;
	idades[iterador]=document.getElementById("idade").value;
	opiniao[iterador]=document.getElementById("opiniao").value;

	if(opiniao[iterador]=="3") soma_idades_opiniao_3+=parseInt(idades[iterador]);
	if(opiniao[iterador]=="2") quantidade_opiniao_2++;
	if(opiniao[iterador]=="3") quantidade_opiniao_3++;
	alert("Opnião do(a) professor(a) "+nomes[iterador]+" recebido com sucesso.")
	iterador++;
	if(iterador===8){
		var media_idades_opiniao_3=(soma_idades_opiniao_3/quantidade_opiniao_3);
		var porcentagem_opiniao_3=(12.5*quantidade_opiniao_3);
		var resposta_1=document.createElement("p");
		resposta_1.innerHTML="Média das idades das pessoas que responderam Benzadeus: "+media_idades_opiniao_3+".";
		document.getElementById("Joker").appendChild(resposta_1);
		var resposta_2=document.createElement("p");
		resposta_2.innerHTML="Quantidade de pessoas que responderam mais ou menos: "+quantidade_opiniao_2+".";
		document.getElementById("Joker").appendChild(resposta_2);
		var resposta_3=document.createElement("p");
		resposta_3.innerHTML="Porcentagem de pessoas que responderam Benzadeus entre todos os espectadores: "+porcentagem_opiniao_3+"%.";
		document.getElementById("Joker").appendChild(resposta_3);

		iterador=0;
		soma_idades_opiniao_3=0;
		quantidade_opiniao_3=0;
		quantidade_opiniao_2=0;
	}
}