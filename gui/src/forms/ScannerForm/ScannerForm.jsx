import { Form } from '../Form/Form'

import style from './scannerform.module.scss'

export const ScannerForm = () => {
	const inputs = [
		{
			'label':	'IPv4',
			'type':		'text',
			'placeholder':	'Введите адрес хоста',
		},
	];

	return (
		<Form
			style={style}
			name='Сканировать'
			inputs={inputs}
			text='Сканировать'
		/>
	)
}
