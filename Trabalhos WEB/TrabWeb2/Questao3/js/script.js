function login(){
	var tamanho_senha=document.getElementById("cSenha").value;
	tamanho_senha=tamanho_senha.length;
	if(tamanho_senha<6){
		alert("Sua senha deve possuir no mímino 6 caracteres.");
	} 
	if(tamanho_senha>=6 && tamanho_senha<=8){
		alert("Senha normal, pode aumentar sua segurança adicionando mais caracteres.");
	}
	if(tamanho_senha>8){
		alert("Senha forte, você está seguro.");
	}
}