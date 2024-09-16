function validarCPF(cpf)
	-- Verificar se o CPF tem 11 dígitos
	if #cpf ~= 11 or not cpf:match("^%d+$") then
			return {valido = false, formatado = "", mensagem = "Não está no formato correto."}
	end

	-- Verificar se todos os dígitos são iguais
	if cpf:match("^(%d)%1*$") then
			return {valido = false, formatado = formatarCPF(cpf), mensagem = "Todos os dígitos são iguais."}
	end

	-- Calcular o primeiro dígito verificador
	local soma = 0
	for i = 1, 9 do
			soma = soma + tonumber(cpf:sub(i, i)) * (11 - i)
	end
	local resto = soma % 11
	local digito1 = resto < 2 and 0 or 11 - resto

	-- Verificar o primeiro dígito verificador
	if tonumber(cpf:sub(10, 10)) ~= digito1 then
			return {valido = false, formatado = formatarCPF(cpf), mensagem = "Primeiro dígito é inválido."}
	end

	-- Calcular o segundo dígito verificador
	soma = 0
	for i = 1, 10 do
			soma = soma + tonumber(cpf:sub(i, i)) * (12 - i)
	end
	resto = soma % 11
	local digito2 = resto < 2 and 0 or 11 - resto

	-- Verificar o segundo dígito verificador
	if tonumber(cpf:sub(11, 11)) ~= digito2 then
			return {valido = false, formatado = formatarCPF(cpf), mensagem = "Segundo dígito é inválido."}
	end

	return {valido = true, formatado = formatarCPF(cpf), mensagem = "CPF válido."}
end

function formatarCPF(cpf)
	return string.format("%s.%s.%s-%s",
			cpf:sub(1, 3),
			cpf:sub(4, 6),
			cpf:sub(7, 9),
			cpf:sub(10, 11)
	)
end

function validarData (data)
	-- Verificar se a data está no formato correto
	if not data:match("%d%d%d%d%-%d%d%-%d%d") then
		return {valido = false, formatado = "", mensagem = "Não está no formato correto."}
	end

	local ano = data:sub(1, 4)
	local mes = data:sub(6, 7)
	local dia = data:sub(9, 10)

	local mesesCom31Dias = {
			["01"] = true,  -- Janeiro
			["03"] = true,  -- Março
			["05"] = true,  -- Maio
			["07"] = true,  -- Julho
			["08"] = true,  -- Agosto
			["10"] = true,  -- Outubro
			["12"] = true   -- Dezembro
	}

	local mesesCom30Dias = {
			["04"] = true,  -- Abril
			["06"] = true,  -- Junho
			["09"] = true,  -- Setembro
			["11"] = true   -- Novembro
	}

	if tonumber(ano) < 1 or tonumber(ano) > 3100 then 
		return {valido = false, formatado = "", mensagem = "Ano não está no range correto."}
	end

	if tonumber(mes) < 1 or tonumber(mes) > 12 then 
		return {valido = false, formatado = "", mensagem = "Mês não está no range correto."}
	end
	
	if mesesCom31Dias[mes] then
		if tonumber(dia) < 1 or tonumber(dia) > 31 then
				return {valido = false, formatado = "", mensagem = "Dia não está no range correto para um mês com 31 dias."}
		end
	elseif mesesCom30Dias[mes] then
		if tonumber(dia) < 1 or tonumber(dia) > 30 then
				return {valido = false, formatado = "", mensagem = "Dia não está no range correto para um mês com 30 dias."}
		end
	elseif mes == "02" then  -- Fevereiro
		if tonumber(dia) < 1 or tonumber(dia) > 29 then
				return {valido = false, formatado = "", mensagem = "Dia não está no range correto para Fevereiro."}
		end
	end

	-- Retorna válido para o caso de estar no formato correto
	return {valido = true, formatado = formatarData(data), mensagem = "Data válida."}
end

function formatarData(data)
	return string.format("%s/%s/%s",
			data:sub(9, 10),
			data:sub(6, 7),
			data:sub(1, 4)
	)
end