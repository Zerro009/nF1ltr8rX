import { FormInput } from '../FormInput/FormInput'

export const Form = ({style, name, inputs, text}) => {
	return (
		<div className={style.form}>
			<div className={style.header}>
				<h1>
					
				</h1>
			</div>
			<div className={style.body}>
				{Object.entries(inputs).map((item, index) => {
					return <FormInput {...inputs[index]} key={index} />
				})}
			</div>
			<button>
				{text}
			</button>
		</div>
	)
}
