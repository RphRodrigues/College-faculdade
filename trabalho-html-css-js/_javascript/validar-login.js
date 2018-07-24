/* Arquivo Javasript */

function validar()
{
	var email = login1.email.value;
	var senha = login1.senha.value;

		if(email == "")
		{	
			alert("Digite seu email");
			login1.email.focus();
			return false;
		}

		if(senha < 8)
		{
			alert("Digite uma senha com no mínimo 8 dígitos");
			login1.senha.focus();
			return false;
		}

		return true;
}