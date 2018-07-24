/* Arquivo Javasript */

function vContato()
{
	var name = form1.nome.value;
	var email = form1.email.value;
	var data = form1.data.value;

		if(name == "")
		{
			alert("Preencha seu nome");
			form1.nome.focus();
			return false;
		}

		if(email == "")
		{
			alert("Preencha seu email");
			form1.email.focus();
			return false;
		}
		if(data == "")
		{
			alert("Preencha sua data de nascimento");
			form1.data.focus();
			return false;
		}

		
	return true;
}