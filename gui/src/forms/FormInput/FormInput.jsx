import { useState } from 'react'

export const FormInput = ({label, type, placeholder}) => {
	const [value, setValue] = useState('')

	const onChangeValue = (e) => {
		setValue(e.target.value)
	}

	return (
		<div>
			<label>
				{label}
			</label>
			<input
				type={type}
				placeholder={placeholder}
				value={value}
				onChange={onChangeValue}
			/>
		</div>
	)
}
