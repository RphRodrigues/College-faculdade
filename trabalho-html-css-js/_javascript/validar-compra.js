/* Arquivo Javasript */

function validar_compra()
{   
	var hamburger = 35;
	var refri = form_compra.refri.value;
	var bat = form_compra.batata.value;
	var tel = form_compra.tel.value;
	var end = form_compra.end.value;
	
	
		if(tel == "")
		{
			alert("Preencha seu telefone");
			form_compra.tel.focus();
			return false;
		}

		if(end == "")
		{
			alert("Preencha seu Endereço");
			form_compra.end.focus();
			return false;
		}

		if(form_compra.refri.checked)
		{
			refri = 15;
		} 
		if(form_compra.batata.checked)
		{
			bat = 10;
		}

		var tot = parseInt(hamburger) + parseInt(refri) + parseInt(bat);  

		alert("Total a pagar: R$" + " " + tot);

	return true;
}