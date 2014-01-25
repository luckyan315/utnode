{
	"targets": [
		{
			"target_name": "func",
			"sources": [ "func.cc" ],
			'conditions':[
				['OS=="linux"', {
					'cflags_cc!': [
						'-fno-exceptions',
					],
					'ldlags!': [
						'-fno-exceptions',
					],
				}, 
				]
			]
		}
	]
}
